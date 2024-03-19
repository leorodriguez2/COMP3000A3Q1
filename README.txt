Leonardo Rodriguez
#101246544

# Student Records Management System

This application is a simple student records management system that connects to a PostgreSQL database to perform CRUD (Create, Read, Update, Delete) operations on student records.

## Setup

1. **Database Setup**:
   - Make sure you have PostgreSQL installed and running on your system.
   - Create a new PostgreSQL database named `my_database` (or any name of your choice).
   - Execute the SQL commands in the `create_schema.sql` file to create the necessary tables and insert initial data into the database.

2. **Compile the Application**:
   - Compile the `student_records.c` file using a C compiler. For example:
     ```
     gcc student_records.c -o student_records -lpq
     ```

3. **Run the Application**:
   - Run the compiled executable:
     ```
     ./student_records
     ```

## Usage

Once the application is running, you can interact with it to perform various operations on student records:

- **Fetch All Students**: Retrieves and displays all records from the `students` table.
- **Add Student**: Inserts a new student record into the `students` table.
- **Update Student Email**: Updates the email address for a student with the specified student ID.
- **Delete Student**: Deletes the record of the student with the specified student ID.