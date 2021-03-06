#ifndef BOARD_SERVICE_H
#define BOARD_SERVICE_H

// Qt
#include <QObject>
#include <QtPositioning/QGeoCoordinate>
#include <QTimer>

// Internal
#include "sns_packet.h"
#include "ins_packet.h"
#include "alt_packet.h"

namespace domain
{
    class BoardService: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(float barAltitude READ barAltitude NOTIFY barAltitudeChanged)
        Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)

        Q_PROPERTY(float pitch READ pitch NOTIFY pitchChanged)
        Q_PROPERTY(float roll READ roll NOTIFY rollChanged)
        Q_PROPERTY(float yaw READ yaw NOTIFY yawChanged)

        Q_PROPERTY(int snsFix READ snsFix NOTIFY snsFixChanged)
        Q_PROPERTY(QGeoCoordinate position READ position NOTIFY positionChanged)
        Q_PROPERTY(float snsYaw READ snsYaw NOTIFY snsYawChanged)
        Q_PROPERTY(float groundSpeed READ groundSpeed NOTIFY groundSpeedChanged)
        Q_PROPERTY(float climb READ climb NOTIFY climbChanged)
        Q_PROPERTY(float snsAltitude READ snsAltitude NOTIFY snsAltitudeChanged)

        Q_PROPERTY(bool altStatus READ altStatus NOTIFY altStatusChanged)
        Q_PROPERTY(bool insStatus READ insStatus NOTIFY insStatusChanged)
        Q_PROPERTY(bool snsStatus READ snsStatus NOTIFY snsStatusChanged)

        Q_PROPERTY(bool altAvalible READ altAvalible NOTIFY altAvalibleChanged)
        Q_PROPERTY(bool insAvalible READ insAvalible NOTIFY insAvalibleChanged)
        Q_PROPERTY(bool snsAvalible READ snsAvalible NOTIFY snsAvalibleChanged)

    public:
        explicit BoardService(QObject* parent = nullptr);

        float barAltitude() const;
        float temperature() const;

        float pitch() const;
        float roll() const;
        float yaw() const;

        int snsFix() const;
        QGeoCoordinate position() const;
        float snsYaw() const;
        float groundSpeed() const;
        float climb() const;
        float snsAltitude() const;

        bool altStatus() const;
        bool insStatus() const;
        bool snsStatus() const;

        bool altAvalible() const;
        bool insAvalible() const;
        bool snsAvalible() const;

    public slots:
        void updateAltData(const AltPacket& packet);
        void updateInsData(const InsPacket& packet);
        void updateSnsData(const SnsPacket& packet);

    signals:
        void barAltitudeChanged(float barAltitude);
        void temperatureChanged(float temperature);

        void pitchChanged(float pitch);
        void rollChanged(float roll);
        void yawChanged(float yaw);

        void snsFixChanged(int snsFix);
        void positionChanged(QGeoCoordinate position);
        void snsYawChanged(float snsYaw);
        void groundSpeedChanged(float groundSpeed);
        void climbChanged(float climb);
        void snsAltitudeChanged(float snsAltitude);

        void altStatusChanged(bool altStatus);
        void insStatusChanged(bool insStatus);
        void snsStatusChanged(bool snsStatus);

        void altAvalibleChanged(bool altAvalible);
        void insAvalibleChanged(bool insAvalible);
        void snsAvalibleChanged(bool snsAvalible);

        void publish(const QString& topic, const QByteArray& data);

    private slots:
        void onTimeout();

    private: // TODO: sepatate to subclasses
        float m_barAltitude;
        float m_temperature;

        float m_pitch;
        float m_roll;
        float m_yaw;

        int m_snsFix;
        QGeoCoordinate m_position;
        float m_snsYaw;
        float m_groundSpeed;
        float m_climb;
        float m_snsAltitude;

        bool m_altStatus;
        bool m_insStatus;
        bool m_snsStatus;

        bool m_altAvalible;
        bool m_insAvalible;
        bool m_snsAvalible;
        QTimer m_altTimer;
        QTimer m_insTimer;
        QTimer m_snsTimer;
    };
}

#endif // BOARD_SERVICE_H
