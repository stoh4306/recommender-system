#include <uuid/uuid.h>
#include <iostream>

int main() {
    uuid_t uuid;
    uuid_generate(uuid);

    char str[37]; // UUIDs are 36 characters plus the null terminator
    uuid_unparse(uuid, str);

    std::cout << "Generated UUID: " << str << std::endl;
    return 0;
}
