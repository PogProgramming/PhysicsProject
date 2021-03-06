﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyHealth : MonoBehaviour
{
    public float health;
    public float maxHealth;
    public bool dead { get; private set; }

    private bool despawnEngage = false;
    private float despawnTimer = 2f;

    public void TakeDamage(float damage)
    {
        health -= damage;

        if (health <= 0)
        {
            health = 0;
            Death();
        }
    }

    public void TakeDamage(float damage, Vector3 velocity, float gunSpeed, Rigidbody bodyPart)
    {
        if (bodyPart.name == "Head")
        {
            health -= damage * 2.5f;
        }
        else
        {
            health -= damage;
        }

        if (health <= 0)
        {
            health = 0;
            Death(velocity, gunSpeed, bodyPart);
        }

        if(transform.tag == "Invincible")
        {
            GetComponent<Rigidbody>().AddForce(-velocity.normalized * (gunSpeed / 3), ForceMode.Impulse);
        }
    }


    float timer = 0;
    void Update()
    {
        if (despawnEngage)
        {
            timer += Time.deltaTime;
            if (timer > despawnTimer)
            {
                Destroy(gameObject);
                GameObject.Find("EventSystem").GetComponent<GameSystem>().AdjustKills(1);
            }
        }
    }

    public void Death()
    {
        if(transform.tag == "Invincible")
        {
            health = maxHealth;
        }
        else
        {
            dead = true;
            EnableRagdoll();
            // send back info like if stats are involved
            despawnEngage = true;

            if (health != 0) health = 0;

        }
    }

    void Death(Vector3 velocity, float gunSpeed, Rigidbody bodyPart)
    {
        dead = true;
        EnableRagdoll();
        //bodyPart.AddForce(-velocity.normalized * (gunSpeed / 2), ForceMode.Impulse);
        // send back info like if stats are involved
        despawnEngage = true;

    }

    void EnableRagdoll()
    {
        GetComponent<NavMeshAgent>().enabled = false;
        GetComponent<Ragdoll>().RagdollOn = true;
    }

}
