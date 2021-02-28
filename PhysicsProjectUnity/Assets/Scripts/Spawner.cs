using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public Transform prefab;
    float timer = 0;

    bool running = false;
    void Start()
    {

    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space)) running = !running;

        if (running && timer >= 5f)
        {
            Instantiate(prefab, transform.position, Quaternion.identity);
            timer = 0;
        }
        timer += Time.deltaTime;
    }
}
