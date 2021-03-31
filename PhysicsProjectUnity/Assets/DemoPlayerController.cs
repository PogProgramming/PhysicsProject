using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DemoPlayerController : MonoBehaviour
{
    Animator aniController;
    CharacterController controller;

    public float movementSpeed = 5f;

    void Start()
    {
        aniController = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();
    }

    void Update()
    {
        float fwd = Input.GetAxis("Vertical");
        float right = Input.GetAxis("Horizontal");
        fwd = Mathf.Clamp(fwd, -0.5f, 1);

        aniController.SetFloat("Forward", fwd);
        aniController.SetFloat("Turn", right);
        aniController.SetFloat("Sense", Mathf.Sign(fwd));

        controller.SimpleMove(Vector3.forward * fwd * Time.deltaTime);
        controller.SimpleMove(Vector3.right * right * Time.deltaTime);
    }
}
