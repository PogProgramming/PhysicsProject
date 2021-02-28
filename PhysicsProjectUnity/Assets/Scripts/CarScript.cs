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

    List<Vector3> spawnPoints = new List<Vector3>();
    Transform[] trans;


    void Start()
    {
        trans = transform.parent.GetComponentsInChildren<Transform>();
        foreach (Transform t in trans)
            spawnPoints.Add(t.position);

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
        if (transform.position.y < -10)
        {
            Transform[] objs = transform.parent.GetComponentsInChildren<Transform>();
            for(int i = 0; i < spawnPoints.Count; i++)
            {
                objs[i].position = spawnPoints[i];
            }
        }
    }
}
