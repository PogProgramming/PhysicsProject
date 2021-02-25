using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarScript : MonoBehaviour
{
    //Wheels
    public HingeJoint backRight;
    public HingeJoint backLeft;
    public HingeJoint frontLeft;
    public HingeJoint frontRight;

    JointMotor backRightMotor;
    JointMotor backLeftMotor;
    JointMotor frontLeftMotor;
    JointMotor frontRightMotor;


    void Start()
    {
        
        HingeJoint[] joints = GetComponents<HingeJoint>();
        {
            backRight = joints[0];
            backLeft = joints[1];
            frontLeft = joints[2];
            frontRight = joints[3];
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
