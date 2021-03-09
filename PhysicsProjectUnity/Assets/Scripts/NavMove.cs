using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavMove : MonoBehaviour
{
    NavMeshAgent agent = null;
    //Vector3 targetPos = Vector3.zero;

    // for testing ill do it this time..
    Transform playerTransform = null;
    Animator animator = null;

    EnemyHealth health;

    void Start()
    {
        playerTransform = GameObject.FindGameObjectWithTag("Player").transform;
        agent = GetComponent<NavMeshAgent>();
        animator = GetComponent<Animator>();
        health = GetComponent<EnemyHealth>();
    }

    void Update()
    {
        if (health.dead) return;

        if(Vector3.Distance(playerTransform.position, transform.position) < 20f)
        {
            agent.SetDestination(playerTransform.position);
            animator.SetFloat("Speed", agent.speed * Time.deltaTime);
        }
        else
        {
            animator.SetFloat("Speed", 0);
        }
    }
}
