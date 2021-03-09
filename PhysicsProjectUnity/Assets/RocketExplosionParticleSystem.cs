using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RocketExplosionParticleSystem : MonoBehaviour
{
    float timer = 0;
    float timerOut = 3f;

    void Start()
    {
 
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        if (timer >= timerOut) Destroy(gameObject);
    }
}
