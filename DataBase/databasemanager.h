#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

/// \warning make shure that you are using compiler native libstdc...dll,
/// but not QT libstdc...dll, or it causes errors
/// see http://forum.qt.io/topic/45306/solved-runtime-error-with-mingw-ifstream-qt-creator/11
#include <fstream>

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>


/// Holds all functionality related to database
/// Use for singe MySQL Database managment
class DatabaseManager : public QObject
{
    Q_OBJECT

        /// This stupid Qt provides access to QSqlDatabase only by the instances,
        /// so i have to create unique names instead unique objects
        /// if i connected then true, else false, if true at destruction, then i have
        /// to destroy QSqlDatabase instance with _myDatabaseConnectionName
    private: bool _isConnectedFlag;
        /// Returns _hasConnection;
    public : bool isConnected() const {return _isConnectedFlag;}
        /// Here should be QSqlDatabase::lastError()
    public : QSqlError lastError() const;
        /// Common constructor,
        /// parent not used

    public : bool connectToDatabase(
                QString hName, QString dbName, QString uName, QString password);
        /// Common destructor
    public : void saveConnectionsToFile(
                QString dbConnectionsFilename = "DBConnections.txt");
    public : QList<QStringList> loadConnectionsFromFile(
                QString dbConnectionsFilename = "DBConnections.txt");

    private: DatabaseManager(QObject *parent = nullptr);
        /// Try to connect to database by given data, returns false if fail or true
        /// opened connection will has name _myDatabaseConnectionName
    private: ~DatabaseManager();

        /// Catch this signal with some Ui or Logger
    public : Q_SIGNAL void writeString(const QString message) const;


    public : static DatabaseManager *instance();
};

#endif // DATABASEMANAGER_H