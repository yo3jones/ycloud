#include <string>
#include "./connection-info.h"

namespace ydb {

void createDatabase(ConnectionInfo defaultConnInfo, const string& databaseName);

}
