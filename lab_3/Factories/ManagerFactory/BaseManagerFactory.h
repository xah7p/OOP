#pragma once

class BaseManagerFactory {
public:
    BaseManagerFactory() = default;
    virtual ~BaseManagerFactory() = default;

    virtual void configureManagerPool() = 0;
};