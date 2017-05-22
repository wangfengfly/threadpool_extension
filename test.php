<?php
$val = threadpool_create(2, 20);
function test(){
        echo "hahah\n";
}
$res = threadpool_add(17, "test");
echo "done\n";