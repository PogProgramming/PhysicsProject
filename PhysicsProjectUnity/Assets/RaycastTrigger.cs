using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RaycastTrigger : MonoBehaviour
{
    public GameObject gate = null;

    bool openGate = false;

    public Vector3 openGateVec = Vector3.zero;
    public Vector3 closeGateVec = Vector3.zero;

    public float gateSpeed = 5f;

    public bool buttonPressed = false;

    public Vector3 buttonNotPressedVec = Vector3.zero;
    public Vector3 buttonPressedInVec = Vector3.zero;

    float buttonTimer = 0;
    public const float buttonPressTime = 1.5f;

    void Start()
    {

    }

    void Update()
    {
        if (buttonPressed)
        {
            buttonTimer += Time.deltaTime;

            if (buttonTimer >= buttonPressTime)
            {
                buttonTimer = 0;
                buttonPressed = false;

                transform.position = buttonNotPressedVec;
            }
        }

        if (openGate)
        {
            gate.transform.localPosition = Vector3.Lerp(gate.transform.localPosition, openGateVec, gateSpeed * Time.deltaTime);

        }
        else if (!openGate)
        {
            gate.transform.localPosition = Vector3.Lerp(gate.transform.localPosition, closeGateVec, gateSpeed * Time.deltaTime);
        }
    }

    public void PressButton()
    {
        if (!buttonPressed)
        {
            buttonPressed = true;
            openGate = !openGate;

            transform.position = buttonPressedInVec;
        }
    }
}
