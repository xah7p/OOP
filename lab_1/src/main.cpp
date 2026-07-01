#include "appargs.h"
#include "action_loop.h"

#define WINDOW_TITLE "Каркасный 3d viewer"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define LOOP_DELAY 10

int main(int argc, char *argv[])
{
    AppArgs args = AppArgsCreate();
    ErrorCode code = AppArgsParse(args, argc, argv);
    if (code == SUCCESS)
    {
        WindowContext *windowContext = WindowContextCreate(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (windowContext)
        {
            code = RunEventLoop(*windowContext, args.filename, LOOP_DELAY);
            WindowContextDestroy(&windowContext);
        }
    }
    ErrorPrint(code);
    return code;
}