#!/bin/bash
if [ -d omg_sql ] ; then
php ./orm.php localhost root "firefly" football role_info omg_sql/
cp omg_sql/* ../orm/
else
    echo "dir [omg_sql] not exist"
fi

