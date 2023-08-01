#ifdef QT_VERSION5X
#include <QRegularExpression>
#else
#include <QRegExp>
#endif

class PatternFinder {
public:
    PatternFinder(QAbstractItemModel* model) : m_model(model) {}

    void findHexPattern(const QString& pattern) {
        if (pattern == ".*") {
            msg("success");
            return;
        }

        QByteArray data;
        recurseData(data, m_model->index(0, 0));

        QString hexData = QString(data.toHex());
#ifdef QT_VERSION5X
        QRegularExpression re(pattern);
        QRegularExpressionMatchIterator it = re.globalMatch(hexData);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            int index = match.capturedStart() / 2;
            int length = match.capturedLength() / 2;
            msg(QString("index: %1, value: %2").arg(index).arg(data.mid(index, length).toHex()));
        }
#else
        QRegExp rx(pattern);
        int pos = 0;
        while ((pos = rx.indexIn(hexData, pos)) != -1) {
            int index = pos / 2;
            int length = rx.matchedLength() / 2;
            msg(QString("index: %1, value: %2").arg(index).arg(data.mid(index, length).toHex()));
            pos += rx.matchedLength();
        }
#endif
    }

    void findGUIDPattern(const QString& pattern) {
        QByteArray data;
        recurseData(data, m_model->index(0, 0));

        QString hexData = QString(data.toHex()).toUpper();
        hexData.insert(8, '-');
        hexData.insert(13, '-');
        hexData.insert(18, '-');
        hexData.insert(23, '-');

        QByteArray guidData;
        QStringList hexValues = hexData.split('-');
        for (int i = 0; i < hexValues.count(); ++i) {
            QByteArray bytes = QByteArray::fromHex(hexValues[i].toUtf8());
            std::reverse(bytes.begin(), bytes.end());
            guidData.append(bytes);
        }

#ifdef QT_VERSION5X
        QRegularExpression re(pattern);
        QRegularExpressionMatchIterator it = re.globalMatch(guidData.toHex());
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            int index = match.capturedStart() / 2;
            int length = match.capturedLength() / 2;
            msg(QString("index: %1, value: %2").arg(index).arg(hexData.mid(index * 3, length * 3 - 1)));
        }
#else
        QRegExp rx(pattern);
        int pos = 0;
        while ((pos = rx.indexIn(guidData.toHex(), pos)) != -1) {
            int index = pos / 2;
            int length = rx.matchedLength() / 2;
            msg(QString("index: %1, value: %2").arg(index).arg(hexData.mid(index * 3, length * 3 - 1)));
            pos += rx.matchedLength();
        }
#endif
    }

    void findTextPattern(const QString& pattern) {
        QByteArray data;
        recurseData(data, m_model->index(0, 0));

        QString textData = QString::fromUtf8(data);
#ifdef QT_VERSION5X
        int index = textData.indexOf(QRegularExpression(pattern));
        if (index != -1) {
            msg(QString("index: %1, value: %2").arg(index).arg(textData.mid(index, pattern.length())));
        }
#else
        int index = textData.indexOf(QRegExp(pattern));
        if (index != -1) {
            msg(QString("index: %1, value: %2").arg(index).arg(textData.mid(index, pattern.length())));
        }
#endif
    }

private:
    QAbstractItemModel* m_model;

    void recurseData(QByteArray& data, const QModelIndex& index) {
        if (index.isValid()) {
            QByteArray headerData = m_model->headerData(index.row(), Qt::Vertical).toByteArray();
            data.append(headerData);

            for (int i = 0; i < m_model->rowCount(index); ++i) {
                recurseData(data, m_model->index(i, 0, index));
            }

            QByteArray bodyData = m_model->data(index, Qt::DisplayRole).toByteArray();
            data.append(bodyData);
        }
    }

    void msg(const QString& message) {
        qDebug() << message;
    }
};