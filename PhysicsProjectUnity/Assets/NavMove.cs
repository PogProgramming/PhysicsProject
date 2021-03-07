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

    void Start()
    {
        playerTransform = GameObject.FindGameObjectWithTag("Player").transform;
        agent = GetComponent<NavMeshAgent>();        
    }

    void Update()
    {
        agent.SetDestination(playerTransform.position);
    }
}
