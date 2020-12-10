//*************************************************************************************************
/*							Exception Definition File
Author: Daniel Kelley
Date: 12/3/2019
Project: Doubly Linked Recursive List
FileName: Exceptions.h
Purpose: This file contains the definitions for all exceptions thrown by
		 OrdListClass.
*/
#pragma once

// Thrown when client tries to insert a key that is already in the list.
class DuplicateKeyException {};

// Thrown whenever OrdListClass catches a bad allocException, when the client
// tries to insert when there is no available memory.
class OutOfMemoryException{};

// Thrown when client requests for a key to be retrieved or deleted that
// does not exist in the list.
class KeyNotThereException {};