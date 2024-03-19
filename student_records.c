#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

// Function to establish a connection to the PostgreSQL database
PGconn *connect_db() {
    const char *conninfo = "dbname=my_database user=postgres";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    return conn;
}

// Function to fetch all students from the database
void getAllStudents(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM students");

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        int cols = PQnfields(res);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%s\t", PQgetvalue(res, i, j));
            }
            printf("\n");
        }
    }

    PQclear(res);
}

// Function to add a new student record into the students table
void addStudent(PGconn *conn, const char *first_name, const char *last_name, const char *email, const char *enrollment_date) {
    const char *query_template = "INSERT INTO students (first_name, last_name, email, enrollment_date) VALUES ('%s', '%s', '%s', '%s')";
    char query[256];
    snprintf(query, sizeof(query), query_template, first_name, last_name, email, enrollment_date);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Error adding student: %s", PQerrorMessage(conn));
    } else {
        printf("Student added successfully\n");
    }

    PQclear(res);
}

// Function to update the email address for a student with the specified student_id
void updateStudentEmail(PGconn *conn, int student_id, const char *new_email) {
    const char *query_template = "UPDATE students SET email = '%s' WHERE student_id = %d";
    char query[256];
    snprintf(query, sizeof(query), query_template, new_email, student_id);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Error updating email: %s", PQerrorMessage(conn));
    } else {
        printf("Email updated successfully\n");
    }

    PQclear(res);
}

// Function to delete the record of the student with the specified student_id
void deleteStudent(PGconn *conn, int student_id) {
    const char *query_template = "DELETE FROM students WHERE student_id = %d";
    char query[256];
    snprintf(query, sizeof(query), query_template, student_id);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Error deleting student: %s", PQerrorMessage(conn));
    } else {
        printf("Student deleted successfully\n");
    }

    PQclear(res);
}

int main() {
    // Connect to the database
    PGconn *conn = connect_db();

    // Perform operations
    printf("1. Fetching all students:\n");
    getAllStudents(conn);

    printf("\n2. Adding a new student:\n");
    addStudent(conn, "Alice", "Wonderland", "alice@example.com", "2023-09-03");
    printf("\n3. Fetching all students after adding a new student:\n");
    getAllStudents(conn);

    printf("\n4. Updating a student's email:\n");
    updateStudentEmail(conn, 1, "john.doe.new@example.com");
    printf("\n5. Fetching all students after updating email:\n");
    getAllStudents(conn);

    printf("\n6. Deleting a student:\n");
    deleteStudent(conn, 3);
    printf("\n7. Fetching all students after deleting a student:\n");
    getAllStudents(conn);

    // Close the connection
    PQfinish(conn);

    return 0;
}
