using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    public GameObject enemyPlayer;
    public Vector3 spawnPos = new Vector3(0f, 0f, 0f);
    void Start()
    {

    }

    public void SpawnEnemy()
    {
        Instantiate(enemyPlayer, spawnPos, Quaternion.identity);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
