#ifndef UTCENTER_DBTOOL_H
#define UTCENTER_DBTOOL_H
#ifdef MYSQL_ENABLE
void DBCheckNode(int argc, char const * argv[]);
void DBCheckAll(int argc, char const * argv[]);
void DBGetAll(int argc, char const * argv[]);
void DBSelect(int argc, char const * argv[]);
void DBmnhash(int argc, char const * argv[]);
#endif // MYSQL_ENABLE
#endif // UTCENTER_DBTOOL_H