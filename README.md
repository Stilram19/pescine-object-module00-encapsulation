# Advanced OOP Pescine - Module 00 (encapsulation)

![](resources/intro.png)

## About

the first module of the advanced pescine of object oriented programming using c++, it's about encapsulation. 
Here is the link to the [subject](https://cdn.intra.42.fr/pdf/pdf/88947/en.subject.pdf)

## Installation && Usage

1. Clone the repository to your local machine:

   ```bash
   git clone git@github.com:Stilram19/pescine-object-module00-encapsulation.git
   ```

3. Navigate to the repository's directory:

    ```bash
    cd pescine-object-module00-encapsulation
    ```

4. Choose an exercise, Compile and Run the program:

   ``` bash
   cd ex00/ && make run
   ```

## Notes:

- **Struct vs Class in C++**:
  - `struct` and `class` can be used interchangeably, but the `class` keyword is more popular in C++.
  - The main difference is the default access control: while everything inside a `class` is private by default, everything inside a `struct` is public by default.
  - The main reason why `structs` exist in C++ is for compatibility with C.
  - So, there is no difference, apart from default encapsulation.

- **Friend Keyword**:
  - This keyword is used with classes and functions. A friend class or function can access the private and protected members. For functions, they can be either global or member functions of other classes.
  - Member functions cannot be declared as friends.
  - For the `std::ostream &operator<<` function, it can be declared as a member function, but the problem is that it can only have one argument. That's why you need to use the `friend` keyword.

- **About Encapsulation**:
  - Encapsulation is wrapping up the data and functions in one unit. It keeps the details of the object hidden and safe from the outside.
  - Data hiding is done using access modifiers (`private`, `public`, `protected`).
  - Encapsulation reduces the complexity of code by hiding the details and using the interface rather than manipulating the data outside the code.

- **Encapsulation vs Abstraction**:
  - Encapsulation hides the details at the implementation level, and abstraction hides the details at the design level.
  - Encapsulation's aim is to hide the internal working of the class so that you can change it without affecting the interface or the design.
  - Encapsulation is there to isolate concerns of classes: a class may depend on another class just by using the interface provided by the other class and without having access to the details.

- **Example of Encapsulation**: Logging into your account, the implementation of verification is hidden from the client.

- **Nested Classes/Structs**: Since logically, there is no `Account` without a `Bank`, you may consider encapsulating the declaration of `Account` within the declaration of `Bank`, thus it won't be accessible from outside the namespace of `Bank`.

- **Subscript Operator Overloading**: It's a very good idea to overload the subscript operator because it makes the code user-friendly (better than setters and getters in some cases).
  - The fact that we're returning a reference to an element in the class, the user may modify it as well as read it. To encapsulate data, you may consider returning a `const` reference for read purposes only.

- **Throw;**: By using `throw;` without specifying an exception object (`throw;`), you re-throw the caught exception as-is, preserving its original type and context, including the stack trace. This ensures that the exception propagates up the call stack with all relevant information intact.

- **Streams**: In computer science, a stream is a sequence of data elements made available over time. It is a concept used to model data flow, where data is processed piece by piece as it becomes available, rather than waiting for the entire dataset to be loaded into memory.
  - Of course, this is done using a buffer (for reading from a file or writing to a file).

- **Endianness**: The order in which the bytes of a word are stored in a computer system counting only byte significance with earliness.
  - **Big Endianness**: Storing the most significant byte in the smallest address.
  - **Little Endianness**: Storing the most significant byte in the biggest address.
  - Big-endianness is the dominant ordering in network protocols, while little-endianness is the dominant ordering for processor architectures.
  - Big-endianness can be referred to as network byte order.



## Find Other Modules:
[Module-00-Encapsulation](https://github.com/Stilram19/pescine-object-module00-encapsulation)
[Module-01-Relationships](https://github.com/Stilram19/pescine-object-module01-Relationship)
[Module-02-UML](https://github.com/Stilram19/pescine-object-module02-UML)
[Module-03-SOLID](https://github.com/Stilram19/pescine-object-module03-SOLID)
[Module-04-Design Patterns](https://github.com/Stilram19/pescine-object-module04-DesignPatterns)
