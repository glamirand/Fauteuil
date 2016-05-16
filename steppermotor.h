#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

class StepperMotor
{
public:
    StepperMotor(int TriggerPinNumber);
    StepperMotor(int TriggerPinNumber, int DirectionPinNumber);
    StepperMotor(int TriggerPinNumber, int DirectionPinNumber, int EnablePinNumber);
    void Start();
    void SetSpeed(int Speed);
    void Stop();
    void Enable();
    void Dislable();


private:
    int m_TriggerPinNumber;
    int m_DirectionPinNumber;
    int m_EnablePinNumber;
    int m_TargetSpeed;
    int m_CurrentSpeed;
    int m_MinTriggerTime;
    bool m_Reverse;
    bool m_Enabled;
    bool m_Run;
    void StepperMotorConstructor(int TriggerPinNumber, int DirectionPinNumber, int EnablePinNumber);
    void Main();
    unsigned int ComputeTime(int Speed);
    void SetReverse();
};

#endif // STEPPERMOTOR_H
