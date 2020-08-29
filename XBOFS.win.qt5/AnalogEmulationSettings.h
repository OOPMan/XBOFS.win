#pragma once
#include <qobject.h>
#include <qsettings.h>
#include <qstring.h>
#include "ui_AnalogEmulationSettingsWidget.h"


const QString SETTINGS_ANALOG_EMULATION_TOGGLE_MODE_STYLE("toggleModeStyle");
const QString SETTINGS_ANALOG_EMULATION_TOGGLE_MODE_BUTTON("toggleModeButton");
const QString SETTINGS_ANALOG_EMULATION_TOGGLE_STICK_STYLE("toggleStickStyle");
const QString SETTINGS_ANALOG_EMULATION_TOGGLE_STICK_BUTTON("toggleStickButton");
const QString SETTINGS_ANALOG_EMULATION_INTERPOLATION_DURATION("interpolationDuration");
const QString SETTINGS_ANALOG_EMULATION_X_AXIS_MINIMUM("xAxisMinimum");
const QString SETTINGS_ANALOG_EMULATION_X_AXIS_MAXIMUM("xAxisMaximum");
const QString SETTINGS_ANALOG_EMULATION_Y_AXIS_MINIMUM("yAxisMinimum");
const QString SETTINGS_ANALOG_EMULATION_Y_AXIS_MAXIMUM("yAxisMaximum");

enum Style { PRESS, HOLD, UNBOUND };
enum Button { GUIDE, VIEW, START, A, B, X, Y, RB, LB, RT, LT };


class AnalogEmulationSettings : public QObject
{
    Q_OBJECT
public:
    AnalogEmulationSettings(QWidget* parent = Q_NULLPTR);

public slots:
    void handleToggleModeStyleIndexChanged(int index);
    void handleToggleModeButtonIndexChanged(int index);
    void handleToggleStickStyleIndexChanged(int index);
    void handleToggleStickButtonIndexChanged(int index);
    void handleInterpolationDurationTextChanged(const QString& text);
    void handleXAxisMinimumValueChanged(int value);
    void handleXAxisMaximumValueChanged(int value);
    void handleYAxisMinimumValueChanged(int value);
    void handleYAxisMaximumValueChanged(int value);

protected:
    Ui::AnalogEmulationSettingsWidget analogEmulationSettingsUi;
    QSettings* settings;
    Style toggleModeStyle = PRESS;
    Button toggleModeButton = GUIDE;
    Style toggleStickStyle = HOLD;
    Button toggleStickButton = VIEW;
    int interpolationDuration = 0;
    int xAxisMinimum = 100;
    int xAxisMaximum = 100;
    int yAxisMinimum = 100;
    int yAxisMaximum = 100;
};

