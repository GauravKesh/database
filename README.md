# MongoDB-Like Database in C++

A lightweight document-oriented database implemented in C++ that mimics basic MongoDB functionality. This project provides CRUD operations for document management with data persistence using a JSON-like storage format.

## Features

- **Document Management**
  - Create and store documents with custom key-value pairs
  - Retrieve documents by ID
  - Update existing documents
  - Delete documents from the database
  
- **Data Storage**
  - Efficient linked list implementation for in-memory storage
  - JSON-based file persistence
  - Automatic data loading and saving

- **User Interface**
  - Interactive command-line interface
  - Simple and intuitive menu system
  - Clear feedback for all operations

## Project Structure

```
database/
├── Makefile
├── README.md
├── SimpleDB        
├── data/
│   └── database.json 
├── include/
│   └── DocumentDB.h   
└── src/
    ├── main.cpp     
    └── main.o       
```

## Prerequisites

- C++ compiler (GCC 4.9+ recommended)
- Make build system
- Basic understanding of C++ programming
- Basic Understanding of MongoDB.

## Installation

1. Clone the repository
```bash
https://github.com/GauravKesh/database.git
cd database
```

2. Build the project
```bash
make
```

## Usage

Run the program:
```bash
./SimpleDB
```

### Available Commands

1. **Insert Document**
   ```
   Choose option: 1
   Enter Document ID: doc1
   Enter fields (key:value): title:Hello content:World
   ```

2. **Find Document**
   ```
   Choose option: 2
   Enter Document ID: doc1
   ```

3. **Update Document**
   ```
   Choose option: 3
   Enter Document ID: doc1
   Enter new fields: title:Updated
   ```

4. **Remove Document**
   ```
   Choose option: 4
   Enter Document ID: doc1
   ```

5. **Display All Documents**
   ```
   Choose option: 5
   ```

6. **Save to File**
   ```
   Choose option: 6
   ```

### Example Document Format

```json
{
  "id": "doc1",
  "fields": {
    "title": "Hello",
    "content": "World"
  }
}
```

## Building from Source

1. Clean the project:
```bash
make clean
```

2. Build the project:
```bash
make
```

3. Run tests (if implemented):
```bash
make test
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/<feature name>`)
3. Commit your changes (`git commit -m 'Add some <feature name>'`)
4. Push to the branch (`git push origin feature/<feature name>`)
5. Open a Pull Request

## Error Handling

The program includes robust error handling for common scenarios:
- Invalid document IDs
- Duplicate documents
- File I/O errors
- Malformed input

## Performance Considerations

- Uses linked list for efficient document insertion
- Minimal memory footprint
- Quick lookup by document ID
- Efficient file I/O operations

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by MongoDB's document-oriented architecture
- Built using modern C++ features
- Implements best practices for data persistence

## Support

For support, please open an issue in the repository.
