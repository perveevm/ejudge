#! /bin/bash

if [ ! -d /home/judges ]
then
    mkdir -p /home/judges
    chown ejudge:ejudge /home/judges
fi

if [ ! -d /home/ej-compile-spool ]
then
    mkdir -p /home/ej-compile-spool
    chown ejudge:ejcompile /home/ej-compile-spool
    chmod 775 /home/ej-compile-spool
fi

if [ ! -d /home/ej-run-spool ]
then
    mkdir -p /home/ej-run-spool
    chown ejudge:ejudge /home/ej-run-spool
    chmod 755 /home/ej-run-spool
fi

if [ ! -d /var/lib/ejudge ]
then
    mkdir -p /var/lib/ejudge
    chown ejudge:ejudge /var/lib/ejudge
fi

if [ ! -d /var/log/ejudge ]
then
    mkdir /var/log/ejudge
    chown ejudge:ejudge /var/log/ejudge
fi

# EJUDGE_MYSQL_USER
# EJUDGE_MYSQL_PASSWORD
# EJUDGE_MYSQL_DATABASE
# EJUDGE_MYSQL_HOST
# EJUDGE_MYSQL_PORT
SECRETFILE=/home/judges/data/mysql_password

mysqlopts=""
[ "${EJUDGE_MYSQL_USER}" != "" ] && mysqlopts="${mysqlopts} --user ${EJUDGE_MYSQL_USER}"
[ "${EJUDGE_MYSQL_PASSWORD}" != "" ] && mysqlopts="${mysqlopts} --password=${EJUDGE_MYSQL_PASSWORD}"
[ "${EJUDGE_MYSQL_DATABASE}" != "" ] && mysqlopts="${mysqlopts} -D ${EJUDGE_MYSQL_DATABASE}"
[ "${EJUDGE_MYSQL_HOST}" != "" ] && mysqlopts="${mysqlopts} --host ${EJUDGE_MYSQL_HOST}"
[ "${EJUDGE_MYSQL_PORT}" != "" ] && mysqlopts="${mysqlopts} --port ${EJUDGE_MYSQL_PORT}"

echo 'show tables;' > cmd.sql
while :
do
    mysql ${mysqlopts} < cmd.sql && break
    sleep 1
done
rm cmd.sql

if [ ! -d /home/judges/data ]
then
    mkdir -p /home/judges/data
    chown ejudge:ejudge /home/judges
    chmod 775 /home/judges
    chown ejudge:ejudge /home/judges/data
    chmod 775 /home/judges/data
    if [ "${EJUDGE_MYSQL_USER}" != "" ]
    then
        echo "${EJUDGE_MYSQL_USER}" > "${SECRETFILE}"
        echo "${EJUDGE_MYSQL_PASSWORD}" >> "${SECRETFILE}"
        echo "${EJUDGE_MYSQL_DATABASE}" >> "${SECRETFILE}"
        echo "${EJUDGE_MYSQL_HOST}" >> "${SECRETFILE}"
        echo "${EJUDGE_MYSQL_PORT}" >> "${SECRETFILE}"
        chown ejudge:ejudge "${SECRETFILE}"
        chmod 600 "${SECRETFILE}"
    fi
    /opt/ejudge/bin/ejudge-install.sh
    /opt/ejudge/bin/ejudge-configure-compilers --batch
    chown ejudge:ejcompile /home/ej-compile-spool
    chmod 775 /home/ej-compile-spool
    touch /home/judges/var/ej-compile.log
    chown ejudge:ejcompile /home/judges/var/ej-compile.log
    chmod 660 /home/judges/var/ej-compile.log
fi

if [ "${EJUDGE_MYSQL_USER}" != "" ]
then
    echo "${EJUDGE_MYSQL_USER}" > "${SECRETFILE}"
    echo "${EJUDGE_MYSQL_PASSWORD}" >> "${SECRETFILE}"
    echo "${EJUDGE_MYSQL_DATABASE}" >> "${SECRETFILE}"
    echo "${EJUDGE_MYSQL_HOST}" >> "${SECRETFILE}"
    echo "${EJUDGE_MYSQL_PORT}" >> "${SECRETFILE}"
    chown ejudge:ejudge "${SECRETFILE}"
    chmod 600 "${SECRETFILE}"
fi

unset EJUDGE_MYSQL_USER
unset EJUDGE_MYSQL_PASSWORD
unset EJUDGE_MYSQL_DATABASE
unset EJUDGE_MYSQL_HOST
unset EJUDGE_MYSQL_PORT

ulimit -Hn 8192
ulimit -n 1024

PATH=/opt/ejudge/bin:$PATH
/opt/ejudge/bin/ejudge-control -u ejudge -g ejudge start

/usr/sbin/httpd -DFOREGROUND
