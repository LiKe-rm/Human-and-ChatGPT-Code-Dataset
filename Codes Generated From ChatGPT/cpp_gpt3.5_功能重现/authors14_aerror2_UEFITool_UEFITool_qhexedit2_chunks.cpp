#include <QtCore>

class Chunks {
public:
    Chunks() : _pos(0), _size(0) {}

    Chunks(QIODevice *device) : _pos(0), _size(0) {
        setIODevice(device);
    }

    void setIODevice(QIODevice *device) {
        _ioDevice = device;
        if (_ioDevice != 0) {
            _ioDevice->seek(0);
            _size = _ioDevice->size();
            _chunks.setData(_ioDevice->readAll());
            _chunks.open(QIODevice::ReadWrite);
            _chunks.seek(0);
        }
    }

    QByteArray read(int maxSize, QByteArray *highlighted = 0) {
        if (maxSize <= 0 || _ioDevice == 0) {
            return QByteArray();
        }
        QByteArray buffer = _chunks.read(maxSize);
        if (highlighted != 0) {
            *highlighted = buffer;
        }
        return buffer;
    }

    void write(int pos, int len, QIODevice *device) {
        if (_ioDevice == 0) {
            return;
        }
        _chunks.seek(pos);
        QByteArray buffer = _chunks.read(len);
        device->write(buffer);
    }

    void setChanged(int pos, bool changed) {
        _changed[pos] = changed;
    }

    bool isChanged(int pos) const {
        return _changed.value(pos, false);
    }

    void insert(int pos, const QByteArray &data) {
        if (_ioDevice == 0) {
            return;
        }
        _chunks.seek(pos);
        _chunks.write(data);
        _size += data.size();
        _changed.insert(pos, true);
    }

    void replace(int pos, int len, const QByteArray &data) {
        if (_ioDevice == 0) {
            return;
        }
        _chunks.seek(pos);
        _chunks.write(data);
        if (len != data.size()) {
            _chunks.remove(pos + data.size(), len - data.size());
        }
        _size += data.size() - len;
        _changed.insert(pos, true);
    }

    void remove(int pos, int len) {
        if (_ioDevice == 0) {
            return;
        }
        _chunks.seek(pos);
        _chunks.remove(len);
        _size -= len;
        _changed.insert(pos, true);
    }

    int find(const QByteArray &ba, int from = 0) const {
        if (_ioDevice == 0) {
            return -1;
        }
        int pos = _chunks.indexOf(ba, from);
        return (pos >= 0) ? (pos + _pos) : -1;
    }

    int rfind(const QByteArray &ba, int from = -1) const {
        if (_ioDevice == 0) {
            return -1;
        }
        int pos = _chunks.lastIndexOf(ba, from - _pos);
        return (pos >= 0) ? (pos + _pos) : -1;
    }

    int pos() const {
        return _pos;
    }

    int size() const {
        return _size;
    }

private:
    QByteArray _chunks;
    QIODevice *_ioDevice;
    int _pos;
    int _size;
    QHash<int, bool> _changed;
};