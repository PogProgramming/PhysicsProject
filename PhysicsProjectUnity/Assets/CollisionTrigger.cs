using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionTrigger : MonoBehaviour
{
    public RaycastTrigger rt = null;

    RunSpawners rs = null;

    void Start()
    {
        rs = GameObject.Find("Spawners").GetComponent<RunSpawners>();
        rs.SpawnEnemies();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.tag == "Player")
        {
            rt.PressButton();
        }
    }
}
