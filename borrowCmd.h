#ifndef BORROWCMD_H
#define BORROWCMD_H

#include "command.h"
#include "commandFactory.h"
#include "movieStore.h"

class BorrowCmd : public Command {
  protected:
    string data;
  public:
    BorrowCmd();
    void execute(MovieStore& store, const vector<string> &vs) const override;
  private:
    char cmd;  // 'B'
};

/**
 * Creating BorrowCmdFactory to make BorrowCmd objects
 * BorrowCmdFactory object will register itself later and get stored in Command class
 */
class BorrowCmdFactory : public CommandFactory {
public:
  BorrowCmdFactory();
  Command *makeCommand(const vector<string> &vs) const override;
};

#endif // BORROWCMD_H