#ifndef YDB_INCLUDE_DRIVER_TRANSACTION_DRIVER_H_
#define YDB_INCLUDE_DRIVER_TRANSACTION_DRIVER_H_

namespace ydb {
namespace driver {

class TransactionDriver {
 public:
  virtual ~TransactionDriver() = default;

  virtual void commit() = 0;
  virtual void abort()  = 0;
};

}  // namespace driver
}  // namespace ydb

#endif  // !YDB_INCLUDE_DRIVER_TRANSACTION_DRIVER_H_
