#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <csignal>
#include <unistd.h>

class ApplicationManager
{
public:
    ApplicationManager() : _argc(0), _argv(nullptr)
    {
        _init();
    }

    ApplicationManager(int argc, char *argv[]) : _argc(argc), _argv(argv)
    {
        _init();
    }

    void RegisterCallback(std::function<int()> callback)
    {
        _Callbacks.push_back(callback);
    }

    void RegisterEventHandler(int fd, std::function<int()> handler)
    {
        _EventHandlers[fd] = handler;
    }

    void UnRegisterEventHandler(int fd)
    {
        _EventHandlers.erase(fd);
    }

    void RegisterSignalHandler(int signal, std::function<void(int)> handler)
    {
        _SignalHandlers[signal] = handler;
        std::signal(signal, SignalHandler);
    }

    void UnRegisterSignalHandler(int signal)
    {
        _SignalHandlers.erase(signal);
    }

    void RunLoop()
    {
        while (!_finished)
        {
            if (_CaughtSignal)
            {
                auto it = _SignalHandlers.find(_CaughtSignal);
                if (it != _SignalHandlers.end())
                {
                    it->second(_CaughtSignal);
                }
                _CaughtSignal = 0;
            }

            for (auto &[fd, handler] : _EventHandlers)
            {
                int result = handler();
                if (result != 0)
                {
                    break;
                }
            }

            if (_Callbacks.empty())
            {
                break;
            }

            for (const auto &callback : _Callbacks)
            {
                int result = callback();
                if (result != 0)
                {
                    _finished = true;
                    break;
                }
            }
        }
    }

private:
    void _init()
    {
        _finished = false;
        _CaughtSignal = 0;
    }

    static void SignalHandler(int signal)
    {
        _CaughtSignal = signal;
    }

    int _argc;
    char **_argv;
    bool _finished;
    static int _CaughtSignal;

    std::vector<std::function<int()>> _Callbacks;
    std::map<int, std::function<int()>> _EventHandlers;
    std::map<int, std::function<void(int)>> _SignalHandlers;
};

int ApplicationManager::_CaughtSignal = 0;

int main(int argc, char *argv[])
{
    ApplicationManager appManager(argc, argv);

    appManager.RegisterCallback([]() -> int {
        std::cout << "Running callback..." << std::endl;
        sleep(1);
        return 0;
    });

    appManager.RegisterSignalHandler(SIGINT, [](int signal) {
        std::cout << "Caught signal: " << signal << std::endl;
        exit(signal);
    });

    appManager.RunLoop();

    return 0;
}
