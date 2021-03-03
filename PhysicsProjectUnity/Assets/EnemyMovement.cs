using System.Collections;
using System.Collections.Generic;
using UnityEditor.Animations;
using UnityEngine;

public class EnemyMovement : MonoBehaviour
{
    CharacterController controller = null;
    Animator animator = null;

    public LayerMask playerMask;
    bool locatedPlayer = false;
    public Vector3 playerPos;

    public float walkSpeed = 20f;
    public float viewDistance = 10f;

    void Start()
    {
        controller = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
    }

    void Update()
    {
        locatedPlayer = false;
        Collider[] cols = Physics.OverlapSphere(transform.position, viewDistance, playerMask);
        foreach (Collider col in cols)
        {
            if (col.transform.tag == "Player")
            {
                locatedPlayer = true;
                playerPos = col.transform.position;
            }
        }

        if (locatedPlayer)
        {
            Vector3 lookAtPos = playerPos;
            lookAtPos.y = 0;
            transform.LookAt(lookAtPos);

            controller.SimpleMove(transform.forward * walkSpeed * Time.deltaTime);
            //controller.SimpleMove(transform.up * Time.fixedDeltaTime);
            animator.SetFloat("Speed", walkSpeed * Time.fixedDeltaTime);
        }
        else
        {
            animator.SetFloat("Speed", 0);
        }
    }
}
