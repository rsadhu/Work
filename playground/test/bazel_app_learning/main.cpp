#include <iostream>
#include "proto/message.pb.h"

int main()
{
    // Create a new Person message
    example::Person person;
    person.set_name("John Doe");
    person.set_id(1234);
    person.set_email("johndoe@example.com");

    // Print the message
    std::cout << "Name: " << person.name() << std::endl;
    std::cout << "ID: " << person.id() << std::endl;
    std::cout << "Email: " << person.email() << std::endl;

    // Serialize the message to a string
    std::string serialized_data;
    person.SerializeToString(&serialized_data);

    // Deserialize the message from the string
    example::Person deserialized_person;
    deserialized_person.ParseFromString(serialized_data);

    // Print the deserialized message
    std::cout << "Deserialized Name: " << deserialized_person.name() << std::endl;
    std::cout << "Deserialized ID: " << deserialized_person.id() << std::endl;
    std::cout << "Deserialized Email: " << deserialized_person.email() << std::endl;

    return 0;
}
