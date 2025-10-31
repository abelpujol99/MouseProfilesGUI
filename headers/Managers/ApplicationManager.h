#pragma once
#include <memory>

class ApplicationManager
{
private:

    static std::unique_ptr<ApplicationManager> _applicationMangerInstance;

    ApplicationManager() = default;

public:

    ~ApplicationManager() = default;

    ApplicationManager(const ApplicationManager& other) = delete;
    ApplicationManager& operator=(const ApplicationManager& other) = delete;
    ApplicationManager(const ApplicationManager&& other) = delete;
    ApplicationManager& operator=(ApplicationManager&& other) = delete;

    static ApplicationManager& GetInstance();

    void Start();
};
