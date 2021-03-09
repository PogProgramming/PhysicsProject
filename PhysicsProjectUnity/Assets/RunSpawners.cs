using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RunSpawners : MonoBehaviour
{
    public void SpawnEnemies()
    {
        BroadcastMessage("SpawnEnemy");
    }
}
