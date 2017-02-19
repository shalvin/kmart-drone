
void cmdGo(int argc, const char** args);
void cmdExit(int argc, const char** args);


typedef void(*CommandFunction)(int argc, const char** args);

static const char* commandWords[] = {
    "go",
    "exit",
};

static CommandFunction commandFunctions[] = {
    cmdGo,
    cmdExit,
};
