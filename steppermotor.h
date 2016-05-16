#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H


class StepperMotor
{
public:
    StepperMotor();
    StepperMotor(int TriggerPinNumber);
    StepperMotor(int TriggerPinNumber, int DirectionPinNumber);
    StepperMotor(int TriggerPinNumber, int DirectionPinNumber, int EnablePinNumber);
    void Lancer();
    static void Boucle();

private:
    int m_TriggerPinNumber;
    int m_DirectionPinNumber;
    int m_EnablePinNumber;
    void StepperMotorConstructor(int TriggerPinNumber, int DirectionPinNumber, int EnablePinNumber);
};

#endif // STEPPERMOTOR_H
