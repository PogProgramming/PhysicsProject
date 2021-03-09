using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    public GameObject enemyPlayer;
    void Start()
    {

    }

    public void SpawnEnemy()
    {
        GameObject enemy = Instantiate(enemyPlayer, transform.position, Quaternion.identity);
        GameObject meshes = enemy.transform.GetChild(0).gameObject;
        SkinnedMeshRenderer[] renderers = meshes.GetComponentsInChildren<SkinnedMeshRenderer>();

        Color randColor = new Color(GetClippedRandomValue(), GetClippedRandomValue(), GetClippedRandomValue(), 1f);
        renderers[1].materials[0].SetColor("_Color", randColor);
        renderers[2].materials[0].SetColor("_Color", randColor);
    }

    float GetRandomValue(float min, float max)
    {
        return Random.Range(min, max);
    }

    float GetClippedRandomValue()
    {
        float option1 = GetRandomValue(1, 100);

        if (option1 >= 50) option1 = 255;
        else option1 = 0;

        return option1;
    }
}
