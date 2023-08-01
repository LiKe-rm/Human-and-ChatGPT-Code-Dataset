#include <iostream>
#include <string>
#include <sqlite3.h>

class DbMigrator {
public:
    static const std::string USER_ID;

    void migrate(sqlite3 *db) {
        createSourcesTable(db);
        createUsersTable(db);
        createScriptsTable(db);
        createScriptVersionsTable(db);
        createCollectionsTable(db);
        createCollectionScriptsTable(db);
        alterTables(db);
    }

private:
    void createSourcesTable(sqlite3 *db) {
        executeSql(db, R"(
            CREATE TABLE IF NOT EXISTS sources (
                id INTEGER PRIMARY KEY,
                source TEXT NOT NULL,
                created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
            );
        )");
    }

    void createUsersTable(sqlite3 *db) {
        executeSql(db, R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT NOT NULL UNIQUE,
                hashed_password TEXT NOT NULL,
                registered_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
            );
        )");
    }

    void createScriptsTable(sqlite3 *db) {
        executeSql(db, R"(
            CREATE TABLE IF NOT EXISTS scripts (
                id INTEGER PRIMARY KEY,
                published INTEGER NOT NULL DEFAULT 0,
                name TEXT NOT NULL,
                source TEXT NOT NULL,
                forked_from_id INTEGER REFERENCES scripts,
                author_id INTEGER NOT NULL REFERENCES users,
                recorded_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
            );
        )");
    }

    void createScriptVersionsTable(sqlite3 *db) {
        executeSql(db, R"(
            CREATE TABLE IF NOT EXISTS script_versions (
                id INTEGER PRIMARY KEY,
                script_id INTEGER NOT NULL REFERENCES scripts,
                name TEXT NOT NULL,
                source TEXT NOT NULL,
                version INTEGER NOT NULL,
                version_slug TEXT NOT NULL,
                committed_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
                UNIQUE (script_id, version),
                UNIQUE (version_slug)
            );
        )");
    }

    void createCollectionsTable(sqlite3 *db) {
        executeSql(db, R"(
            CREATE TABLE IF NOT EXISTS collections (
                id INTEGER PRIMARY KEY,
                owner_id INTEGER NOT NULL REFERENCES users,
                name TEXT NOT NULL,
                registered_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
            );
        )");
    }

    void createCollectionScriptsTable(sqlite3 *db) {
        executeSql(db, R"(
            CREATE TABLE IF NOT EXISTS collection_scripts (
                id INTEGER PRIMARY KEY,
                collection_id INTEGER NOT NULL REFERENCES collections,
                script_id INTEGER NOT NULL REFERENCES scripts,
                added_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
            );
        )");
    }

    void alterTables(sqlite3 *db) {
        executeSql(db, "ALTER TABLE scripts DROP COLUMN IF EXISTS published;");
        executeSql(db, "ALTER TABLE script_versions ADD COLUMN IF NOT EXISTS published INTEGER NOT NULL DEFAULT 0;");
    }

    void executeSql(sqlite3 *db, const std::string& sql) {
        char *error_message = nullptr;
        int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error_message);

        if (result != SQLITE_OK) {
            std::cerr << "SQL error: " << error_message << std::endl;
            sqlite3_free(error_message);
        }
    }
};

const std::string DbMigrator::USER_ID = "37cc9dec-0644-44d2-8f90-c40c3030d386";
