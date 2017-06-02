# threadpool_extension
thread pool extension for php



函数说明：
threadpool_create($thread_count, $max_task_num)  
第一个参数是线程池中的线程数，第二个参数是线程池可接受的最大的任务数。  
threadpool_add($task_num, $func_name)  
第一个参数是往线程池中添加的任务数，第二个参数是php中的字符串函数名。  

用法代码请见test.php    
