show engines;

show variables like '%default%';

show variables like 'max_connections'; -- 151

show variables like '%engine%';

show variables like '%char%';

show status like '%thread%';

show charset;

show collation like '%utf8mb4%';

show variables like '%dir%';

show variables like 'innodb_page_size'; -- 16384

show variables like '%format%';

SELECT USER(); -- 'root@localhost'
