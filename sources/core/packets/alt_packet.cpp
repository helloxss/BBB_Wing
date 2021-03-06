#include "alt_packet.h"

using namespace domain;

QDataStream& AltPacket::operator >>(QDataStream& stream) const
{
    stream << status;
    if (!status) return stream;

    stream << altitude;
    stream << temperature;

    return stream;
}

QDataStream& AltPacket::operator <<(QDataStream& stream)
{
    stream >> status;
    if (!status) return stream;

    stream >> altitude;
    stream >> temperature;

    return stream;
}

AltPacket AltPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    AltPacket packet;
    stream >> packet;
    return packet;
}
