<?php
$val = threadpool_create(2, 10);
function test(){
        echo "hahah\n";
}
$res = threadpool_add( "test");
echo "done\n";