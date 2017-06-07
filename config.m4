dnl $Id$
dnl config.m4 for extension pthread_pool

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(pthread_pool, for pthread_pool support,
dnl Make sure that the comment is aligned:
[  --with-pthread_pool             Include pthread_pool support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(pthread_pool, whether to enable pthread_pool support,
dnl Make sure that the comment is aligned:
dnl [  --enable-pthread_pool           Enable pthread_pool support])

if test "$PHP_PTHREAD_POOL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-pthread_pool -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/pthread_pool.h"  # you most likely want to change this
  dnl if test -r $PHP_PTHREAD_POOL/$SEARCH_FOR; then # path given as parameter
  dnl   PTHREAD_POOL_DIR=$PHP_PTHREAD_POOL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for pthread_pool files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PTHREAD_POOL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PTHREAD_POOL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the pthread_pool distribution])
  dnl fi

  dnl # --with-pthread_pool -> add include path
  dnl PHP_ADD_INCLUDE($PTHREAD_POOL_DIR/include)

  dnl # --with-pthread_pool -> check for lib and symbol presence
  dnl LIBNAME=pthread_pool # you may want to change this
  dnl LIBSYMBOL=pthread_pool # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PTHREAD_POOL_DIR/$PHP_LIBDIR, PTHREAD_POOL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PTHREAD_POOLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong pthread_pool lib version or lib not found])
  dnl ],[
  dnl   -L$PTHREAD_POOL_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PTHREAD_POOL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pthread_pool, pthread_pool.c, $ext_shared)
fi
