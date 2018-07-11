ReqBase Requirements Database
=============================

Installation
------------

### Local Install

1. Create empty database in MySQL (e.g., reqbase_dev)
2. Create MySQL user (e.g., reqbase_dev)
3. Get the database file public-dump-final.sql.gz
4. Gunzip it: gunzip DUMP-FILE
5. Load database: mysql -u reqbase_dev -p reqbase_dev < UNZIPPED-FILE
6. Clone ReqBase
7. Copy htdocs/sites/default/reqbase-settings.php to htdocs/sites/default/settings.php
8. Adjust settings.php to your needs (just the password, if you use reqbase_dev)
9. Make htdocs accessible via Apache (see Drupal manual for details)
10. Log in as user 'dev-admin' (password: password)

### Update

1. Update your GIT repository
2. Download recent database dump
3. Empty your database (e.g., reqbase_dev)
4. Reload database using steps above

Database
--------

The database is the original database including all users. It has been stripped of passwords and email adresses
using drush sql-sanitize. You can log in as one of the users or as dev-admin using the standard password 'password'.
