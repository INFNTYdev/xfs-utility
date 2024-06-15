# Extensible File System Utility (XFS Utility)
###### INFINITY Systems, LLC. 2024

<br/>

*about*
<br/>
The XFS (***Extensible File System Utility***) library consist of common tools necessary for dealing with file related operations. These tools are built into an ecosystem of compatible interconnecting components where relationships are present. The XFS ecosystem is designed open to avoid the neglect of standard C++ types which increases usability and compatibility.

<br/>

# Table of Contents
>
> ## 1. [System Path](#system-path)
> ## 2. [Dynamic File Buffer](#dynamic-file-buffer)
> ## 3. [System File](#system-file)
> ## 4. [System Directory](#system-directory)

<br/>

# System Path

<br/>

The XFS system path suite provides safety and simplicty when dealing with strings that represent system paths. The encompassed ***PathT*** namespace is the backbone of path string parsing and can be used standalone with standard string objects. String optimization is an important factor to this project, efforts are made to avoid string copying where possible.

<br/>

> ## **Introduction**
> n/a

<br/>

## Entities
```cpp
namespace PathT


class SystemPath;
```

<br/>

---

<br/>
<br/>

# Dynamic File Buffer

<br/>

The XFS file buffer suite is designed to expose segments of files to memory in *'pages'*, a set interval of characters within a files contents. The core philosophy of this system is simple:
> ### 1) Minimize resource consumption
> ### 2) Offer a friendly interface for developers

<br/>

There are two primary classes presented in this project, ***FileInputBuffer*** and ***FileOutputBuffer***, both of which use the same interface to interact with system files. These types are built upon trivial C++ types; **there are no special dependancies required**.

<br/>

> ## **Introduction**
> When buffering file contents into memory, we may not always know where that file ends. The ***BufferPage*** class is privy to this idea by nature, it accepts three arguments during construction: *page size*, *page index*, and *start index*. With this information we can calculate the appropriate stop index and ensure a ***BufferPage*** never allocates an unreasonable amount of memory. In the case that the full page size produces surplus memory, a reallocation occurs to obtain the exact amount of memory required to hold the contents. This typically happens when a pages buffer size is greater than the file being accessed, or on the final page of a sequence. Additionally, memory allocations for page contents do not take place until the request is made to cache the page. If for any reason the cache operation fails, either no memory is obtained or any memory obtained is released. A ***BufferPage*** knows nothing of the file its contents populate from other than the range of character indecies to retain.

<br/>

## Entities
```cpp
class BufferPage;

class FileInputBuffer;

class FileOutputBuffer;
```

<br/>

---

<br/>
<br/>

# System File

<br/>

n/a

<br/>

> ## **Introduction**
> n/a

<br/>

## Entities
```cpp
```

<br/>

---

<br/>
<br/>

# System Directory

<br/>

n/a

<br/>

> ## **Introduction**
> n/a

<br/>

## Entities
```cpp
```

<br/>

---

<br/>
<br/>

