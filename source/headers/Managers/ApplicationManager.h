#pragma once

class ApplicationManager
{
public:

    ~ApplicationManager() = default;

    ApplicationManager(const ApplicationManager& other) = delete;
    ApplicationManager& operator=(const ApplicationManager& other) = delete;
    ApplicationManager(ApplicationManager&& other) = delete;
    ApplicationManager& operator=(ApplicationManager&& other) = delete;

    static ApplicationManager& GetInstance();

    void Start();


private:

    static ApplicationManager _applicationMangerInstance;

    ApplicationManager() = default;
};
