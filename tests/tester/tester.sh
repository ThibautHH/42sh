#!/bin/bash

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"
TRAPSIG=0

test_field()
{
  local test_body=`tac ./tests/tester/tests | sed -n "/^\[$1\]$/q;p" | tac | sed -n "/^\[$1-END\]$/q;p"`
  [ -z $2 ] && echo "$test_body" || echo "$test_body" | grep -oP '(?<='"$2"'=").*(?=")'
}

run_test()
{
  local runner="/tmp/.runner.$$"

  touch $runner; chmod +x $runner
  echo "#!$MYSHELL
$SETUP
$TESTS" > $runner
  $runner >$mysh_out 2>&1
  echo "
Shell exit status: $?" >> $mysh_out
  echo "#!$REFER
$SETUP
$TCSHUPDATE
$TESTS" > $runner
  $runner >$refsh_out 2>&1
  echo "
Shell exit status: $?" >> $refsh_out
  rm -f $runner
}

load_test()
{
  SETUP=`test_field "$id" SETUP`
  NAME=`test_field "$id" NAME`
  TESTS=`test_field "$id" | tac | sed -n '/\s*TESTS\s*=\s*/q;p' | tac`
  [ -z "$NAME" ] && NAME="Test $id"
  [ -z "$TESTS" ] && TESTS="echo No tests"
  refsh_out="/tmp/.refer.$$"
  mysh_out="/tmp/.myshell.$$"
  run_test
  ko=0
  diff -q $refsh_out $mysh_out >/dev/null 2>&1 || ko=1

  if [ $ko -eq 0 ]
  then
    if [ $dbglvl -ge 1 ]
    then
      echo "Test $id ($NAME): OK"
      if [ $dbglvl -eq 2 ]
      then
        echo "'$MYSHELL' output:"
        cat -e $mysh_out
        echo
        echo "'$REFER' output:"
        cat -e $refsh_out
        echo; echo
      fi
    else
      echo "Test $id: OK"
    fi
    return 0
  else
    [ $always_successful -eq 0 ] && ret=1
    if [ $dbglvl -lt 1 ]
    then
      echo "Test $id: KO"
      return 1
    fi
    echo "Test $id ($NAME): KO - Check output in /tmp/myshell-tests.$$/$id/"
    mkdir -p /tmp/myshell-tests.$$/$id 2>/dev/null
    cp $mysh_out /tmp/myshell-tests.$$/$id/myshell.out
    cp $refsh_out /tmp/myshell-tests.$$/$id/refshell.out
    if [ $dbgerr -eq 1 ]
    then
      echo "'$MYSHELL' output:"
      cat -e $mysh_out
      echo
      echo "'$REFER' output:"
      cat -e $refsh_out
      echo; echo
    fi
    return 1
  fi
}

if [ $TRAPSIG -eq 1 ]
then
  for sig in `trap -l`
  do
    echo "$sig" | grep "^SIG" >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      trap "echo Received signal $sig!" $sig
    fi
  done
fi

[ ! -f ./tests/tester/tests ] && echo "No tests file. Please read README.md" >&2 && exit 1
first_word() {
  echo "$1" | grep -oP '^\S*'
}
for shell_bin in `first_word $MYSHELL` `first_word $REFER`; do
  [ ! -f $shell_bin ] && echo "$shell_bin: No such file or directory." >&2 && exit 1
  [ ! -x $shell_bin ] && echo "$shell_bin: Permission denied." >&2 && exit 1
done

dbglvl=1
dbgerr=0
always_successful=0
tests_list=""
while :; do
  case "$1" in
    -d)
      dbglvl=2
      ;;
    -q)
      dbglvl=0
      ;;
    --debug-errors)
      dbgerr=1
      ;;
    --always-succeed)
      always_successful=1
      ;;
    *)
      tests_list="$tests_list $1"
      ;;
  esac
  shift
  [ -z "$1" ] && break
done
tests_list=`xargs <<< "$tests_list"`
[ $dbglvl -eq 2 ] && echo "Debug mode
Shell: $MYSHELL
Reference: $REFER" >&2
[ -z "$tests_list" ] && tests_list=`cat ./tests/tester/tests | grep -oP "(?<=^\[)[0-9]+(?=\]$)"`
path_backup=$PATH
ret=0
for id in $tests_list; do load_test; done
export PATH=$path_backup
exit $ret
