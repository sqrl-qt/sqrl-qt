#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>

SqrlIdentity::SqrlIdentity() {
}

bool SqrlIdentity::createIdentity() {
  // Creating a new SQRL identity.
  // **LOTS** of entropy here.
  qDebug() << "LOTS of entropy goes here";
  qDebug() << "Security warning: don't use this key for anything but testing!";

  qDebug() << "Currently the key is HARD-CODED!! Very bad!!";
  const char* key = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  QByteArray keyBytes = QByteArray::fromHex(key);
  this->key = keyBytes;

  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);

  if (file.open(QIODevice::WriteOnly)) {
    file.write(this->key);
  }

  return true;
}

/*
 * Load a SQRL identity from file.
 * In case of failure, return false, otherwise, return true.
 */
bool SqrlIdentity::loadIdentity() {
  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);
  QByteArray key;

  if (file.open(QIODevice::ReadOnly)) {
    key = file.readLine();
  }

  if (key.size() == 32) {
    this->key = key;
    return true;
  }
  else {
    return false;
  }
}

QByteArray SqrlIdentity::getKey() {
  return this->key;
}

QString SqrlIdentity::getHexKey() {
  return this->key.toHex();
}
