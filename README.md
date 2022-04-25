<!-- *********************************************************************** -->
<!--                                                                         -->
<!--                                +###****.                                -->
<!--                                =***@@@+                                 -->
<!--            *%*   -%%:  -*%%%#     :@@@=:   #%##%%#=-*%%%*:              -->
<!--            %@%   =@@: #@@*=+*.    -==*@@+  @@@*=+@@@%+=#@@=             -->
<!--            %@%   -@@:-@@-     .==.    *@@. %@#   =@@:   %@#             -->
<!--            +@@+-=%@@..%@@+--+..%@@+--*@@*  @@#   +@@:   @@#             -->
<!--             -*%@@#+.   =#%@@%.  -*%@@%*-   %@*   =@@:   %@*             -->
<!--                                                                         -->
<!-- README.md                                                               -->
<!--                                                                         -->
<!-- By: aperez-b <100429952@alumnos.uc3m.es>                                -->
<!--                                                                         -->
<!-- Created: 2022/04/25 07:29:22 by aperez-b                                -->
<!-- Updated: 2022/04/25 11:02:05 by aperez-b                                -->
<!--                                                                         -->
<!-- *********************************************************************** -->

# ABE-Scalability | Uc3m

[Uc3m] Cybersecurity practice to measure the scalability and complexity of Attribute-Based Encryption

By Alejandro Pérez Bueno (100429952@alumnos.uc3m.es)

### Table of Contents

- [Introduction](#introduction)
- [Code Implementation](#code-implementation)
- [Testing the Algorithm](#testing-the-algorithm)
	- [Graph](#graph)
- [How to Run the Program](#how-to-run-the-program)
	- [Example](#example)
- [Summary](#summary)

## Introduction

The goal for this project is to get familiar with the ``cpabe`` tools for attribute-based encryption. We are asked to code an algorithm that creates various users and their secret keys made from a set of attributes, and later encrypt and decrypt a 5MB pdf file several times. In this practice we will try different combinations of the number of users, attributes and repetitions. The idea is to measure how long it takes to encrypt and decrypt the pdf file depending on these values

## Code Implementation

I implemented the algorithm for encryption in ``C``, since it is what I'm most comfortable coding in. The project includes a ``Makefile`` with the necessary compliation rules. It will create the executable file ``cp_abe`` inside a ``./bin`` folder. This program always takes three arguments:


```
usage: cp_abe <n_users> <n_attributes> <n_repetitions>
```

Here is a quick overview of the functions I created:

| Function | Description |
| :------: | :---------: |
| ``parse_args`` | Reads arguments from ``argv`` and saves number of users, attributes and repetitions |
| ``create_dirs`` | Creates ``tests`` folder where all users' folders will be, and runs ``cpabe-setup`` in ``tests/master`` |
| ``config_dirs`` | Creates folder for every user and creates attributes for all of them |
| ``get_time`` | Returns current ``epoch`` time (seconds since 1970) |
| ``get_str`` | Adds given index to provided string (eg ``"user_1"``, ``"attr_3"``, ``"file_n"``) |
| ``wrap_cmd`` | Joins up to three strings together (used to create command strings) |
| ``crypt_pdf`` | For every ``n_repeat``, encrypts the pdf and then every user decrypts it |
| ``encrypt_pdf`` | Encrypts pdf file ``file.pdf`` with all attributes as ``file-enc.pdf.cpabe`` |
| ``decrypt_pdf`` | Decrypts pdf for a given user and saves it to the user's folder |

Here are the builtin functions I used and a quick description of what they do. Check their manpages for more information

| Function | Description |
| :------: | :---------: |
| ``system`` | Runs a command from the system (used mainly for cpabe commands) |
| ``gettimeofday`` | Returns ``epoch`` in a ``timeval`` struct |
| ``open`` | Opens a file to a file descriptor |
| ``close`` | Closes a file descriptor |
| ``write`` | Writes bytes to a file descriptor |
| ``printf`` | Prints string to ``stdout`` |
| ``malloc`` | Allocates bytes of memory to a given pointer |
| ``free`` | Frees allocated memory from a pointer |
| ``chdir`` | Changes the system's current working directory (same as ``cd`` in a shell)|

Additionally, this project uses a personal library I use called ``libft``. This project only includes the compiled ``libft.a`` file, but the source code for these functions can be found [here](https://github.com/madebypixel02/libft). Here's a quick overview of the functions I used from this personal library:

| Function | Description |
| :------: | :---------: |
| ``ft_putstr_fd`` | Writes a custom string to a file descriptor with ``write`` |
| ``ft_atoi`` | Converts ascii to int. Reads a string and obtains the equivalent integer value |
| ``ft_strdup`` | Returns allocated copy of a string |
| ``ft_strjoin`` | Joins two strings together in an allocated string |
| ``ft_substr`` | Returns allocated substring (copies n bytes from ``start`` of the given string) |


* General Code description

The code of this practice is hopefully easy to read, but it is actually pretty straightforward. Here is a rough list of the instructions it goes over:

1. Read arguments from ``argv`` (argument list) to save ``n_usrs``, ``n_attrs`` and ``n_rep``.
2. Deletes ``tests/`` folder (if present), creates ``tests/master/`` folder, runs ``cpabe-setup`` in it.
3. In the ``tests/`` folder, creates folder for every user (``user_1``, ``...``, ``user_n``), copies ``pub_key`` and creates ``priv`` key with their attributes (``attr_1``, ``...``, ``attr_n``) using ``cpabe-keygen``.
4. Opens log file ``log.txt`` in the ``tests/`` folder where basic logging information will be saved.
5. Stores current time before starting encryption.
6. Repeats ``n_rep`` times the process of encrypting the file ``file.pdf`` with all attributes and then decrypting it for every user in their user folder as (``file_1.pdf``, ``...``, ``file_n.pdf``)
7. Stores current time after encryption.
8. Prints ``end_time`` - ``start_time``, closes ``log.txt`` and exits


## Testing the Algorithm

For this part, we will take a look at the time it takes to encrypt and decrypt a file 20 times depending on the number of users and attributes for every user. Then we'll make a graph to better visualize the results.

| No. of Users | No. of Attributes | Avg. Execution time (seconds) |
| :----------: | :---------------: | :---------------------------: |
| 5 | 5 | 11 |
| 5 | 20 | 17 |
| 20 | 5 | 35 |
| 20 | 20 | 54 |

Note: these values are highly dependant on the processing power of the device running the program. It is only interesting to see the variations in time relative to each other, rather than the actual numbers.

* Key Sizes

To view the key sizes, I thought I'd use something like the following:

```
cat -e tests/master/master_key | wc -c
```

Master Key Size (bytes): 325

| No. of Attributes | Secret Key Size |
| :---------------: | :-------------: |
| 5 | 3288 |
| 20 | 12340 |
| 50 | 30771 |

As we can see, the key size increases very fast as the number of attributes goes up.

### Graph

<p align="center">
  <img src=https://user-images.githubusercontent.com/40824677/165048577-86ebe4fb-9130-4db7-85da-90dfcc15190e.png />
</p>

Note: I added a few extra rows of data to the graph for better visualization.

From the graph we can see a clear pattern. As expected, the more users and attributes, the longer it will take to encrypt and decrypt the file 20 times. However, we can see that changing them number of attributes doesn't affect the performance of the encryption nearly as much as increasing the number of users does. This is easily seen with the case of 5 users and 50 attributes, which roughly takes 30 seconds to finish. However, the inverse case of 50 users and 5 attributes per user takes more than double the time, taking almost 90 seconds to complete.

Thus, we can confidently say that it will be computationally less feasible to have 1k users than having 1k attributes per user.

## How to Run the Program

* Installation

In order to run this practice, you must install some packages on your system. To build the packages, you must first install these dependencies:

```shell
sudo apt -y install make gcc g++ autoconf libc6 libpcre3 
flex bison libgmp-dev libssl-dev libglib2.0-dev help2man
```

Once those dependencies are satisfied, follow these steps to build the required packages on your system (needs root/sudo)

```shell
# pbc
wget https://crypto.stanford.edu/pbc/files/pbc-0.5.14.tar.gz
tar zxvf pbc-0.5.14.tar.gz; cd pbc-0.5.14
autoconf
./configure
make
sudo make install
cd ..

# libbswabe
wget http://acsc.cs.utexas.edu/cpabe/libbswabe-0.9.tar.gz
tar zxvf libbswabe-0.9.tar.gz; cd libbswabe-0.9
./configure
make
sudo make install
cd ..

# cpabe
wget http://acsc.cs.utexas.edu/cpabe/cpabe-0.11.tar.gz
tar zxvf cpabe-0.11.tar.gz; cd cpabe-0.11
./configure --with-pbc-include=/usr/local/include/pbc --with-pbc-lib=/usr/local/lib
sed -e '67 s/\$1/\$1;/' policy_lang.y > temp
mv temp policy_lang.y
make LDFLAGS="-lgmp -lpbc -lcrypto -L/usr/lib/x86_64-linux-gnu -lglib-2.0 -lbswabe -lgmp"
sudo make LDFLAGS="-lgmp -lpbc -lcrypto -L/usr/lib/x86_64-linux-gnu -lglib-2.0 -lbswabe -lgmp" install
cd ..
```


* Usage

As previously mentioned, this project includes a Makefile with all the needed instructions, here's an overview of the commands you can use:

```
make/make all		compiles executable cp_abe to bin/ directory
make clean		cleans object files in obj/ directory
make fclean		calls clean rule and deletes cp_abe executable
make re			cleans up everything and compiles again
make norminette		Runs C linter (norminette) on all required files
```

The Makefile compliles the executable ``cp_abe`` to a folder called ``bin/``. To run the file, specify the path to the executable:

```
./bin/cp_abe 5 5 20
```
Note: if you get an error saying permission denied, try ``chmod +x ./bin/cp_abe`` before executing the file

### Example

## Summary

April 25th, 2022