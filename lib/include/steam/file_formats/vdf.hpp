#pragma once

#include <steam.hpp>
#include <steam/helpers/fs.hpp>
#include <steam/helpers/file.hpp>

#include <variant>
#include <vector>
#include <map>

namespace steam {

    class VDF {
    public:
        VDF() = default;
        explicit VDF(const std::fs::path &path) : m_content(parse(fs::File(path, fs::File::Mode::Read).readBytes())) { }
        explicit VDF(const std::vector<u8> &content) : m_content(parse(content)) { }

        enum class Type : u8 {
            Set = 0x00,
            String = 0x01,
            Integer = 0x02,
            EndSet = 0x08
        };

        struct Value {
            std::variant<std::string, u32, std::map<std::string, Value>> content;

            [[nodiscard]]
            std::string& string() {
                return std::get<std::string>(content);
            }

            [[nodiscard]]
            const std::string& string() const {
                return std::get<std::string>(content);
            }

            [[nodiscard]]
            u32& integer() {
                return std::get<u32>(content);
            }

            [[nodiscard]]
            const u32& integer() const {
                return std::get<u32>(content);
            }

            [[nodiscard]]
            Value& operator[](const std::string &key) & {
                return std::get<std::map<std::string, Value>>(content).at(key);
            }

            [[nodiscard]]
            Value&& operator[](const std::string &key) && {
                return std::move(std::get<std::map<std::string, Value>>(content).at(key));
            }

            [[nodiscard]]
            Value& operator[](const char *key) & {
                return std::get<std::map<std::string, Value>>(content).at(key);
            }

            [[nodiscard]]
            Value&& operator[](const char *key) && {
                return std::move(std::get<std::map<std::string, Value>>(content).at(key));
            }

            auto& operator=(u32 value) {
                this->content = value;
                return *this;
            }

            auto& operator=(const std::string &value) {
                this->content = value;
                return *this;
            }

            auto& operator=(const std::map<std::string, Value> &value) {
                this->content = value;
                return *this;
            }

            [[nodiscard]]
            explicit operator const std::string&() const {
                return this->string();
            }

            [[nodiscard]]
            explicit operator std::string() {
                return this->string();
            }

            [[nodiscard]]
            explicit operator const u32&() const {
                return this->integer();
            }

            [[nodiscard]]
            explicit operator u32() {
                return this->integer();
            }

            bool operator==(const Value &other) const {
                return this->content == other.content;
            }

            bool operator!=(const Value &other) const {
                return this->content != other.content;
            }

        };

        struct KeyValuePair {
            std::string key;
            Value value;
        };

        [[nodiscard]]
        Value& operator[](const char *key) {
            return this->m_content.at(key);
        }

        [[nodiscard]]
        const Value& operator[](const char *key) const {
            return this->m_content.at(key);
        }

        [[nodiscard]]
        Value& operator[](const std::string &key) {
            return this->m_content.at(key);
        }

        [[nodiscard]]
        const Value& operator[](const std::string &key) const {
            return this->m_content.at(key);
        }

        [[nodiscard]]
        std::map<std::string, Value>& get() {
            return this->m_content;
        }

        [[nodiscard]]
        const std::map<std::string, Value>& get() const {
            return this->m_content;
        }

        [[nodiscard]]
        std::vector<u8> dump() const;

        [[nodiscard]]
        std::string format() const;

        bool operator==(const VDF &other) const {
            return this->m_content == other.m_content;
        }

        bool operator!=(const VDF &other) const {
            return this->m_content != other.m_content;
        }

    private:
        std::map<std::string, Value> parse(const std::vector<u8> &data);

        std::map<std::string, Value> m_content;
    };

    bool operator==(u8 byte, VDF::Type type) {
        return static_cast<VDF::Type>(byte) == type;
    }

}