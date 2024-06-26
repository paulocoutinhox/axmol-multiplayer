#pragma once

#include "Colyseus/Serializer/schema.h"
#include "PlayerSchema.hpp"
#include <typeindex>
#include <typeinfo>

using namespace colyseus::schema;

class RoomStateSchema : public Schema {
public:
    MapSchema<PlayerSchema *> *players;

    RoomStateSchema() {
        this->players = new MapSchema<PlayerSchema *>();
        this->_indexes = {{0, "players"}};
        this->_types = {{0, "map"}};
        this->_childPrimitiveTypes = {};
        this->_childSchemaTypes = {{0, typeid(PlayerSchema)}};
    }

    virtual ~RoomStateSchema() {
        delete this->players;
    }

protected:
    inline MapSchema<char *> *getMap(const std::string &field) override {
        if (field == "players") {
            return reinterpret_cast<MapSchema<char *> *>(this->players);
        }
        return Schema::getMap(field);
    }

    inline void setMap(const std::string &field, MapSchema<char *> *value) override {
        if (field == "players") {
            this->players = reinterpret_cast<MapSchema<PlayerSchema *> *>(value);
            return;
        }
        Schema::setMap(field, value);
    }

    inline Schema *createInstance(std::type_index type) override {
        if (type == typeid(PlayerSchema)) {
            return new PlayerSchema();
        }
        return Schema::createInstance(type);
    }
};
