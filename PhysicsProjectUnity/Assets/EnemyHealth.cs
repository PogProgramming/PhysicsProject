using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyHealth : MonoBehaviour
{
    public float health;
    public float maxHealth;

    void Start()
    {

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

        if (health < 0)
        {
            health = 0;
            Death(velocity, gunSpeed, bodyPart);
        }
    }

    void Update()
    {

    }

    void Death(Vector3 velocity, float gunSpeed, Rigidbody bodyPart)
    {
        EnableRagdoll();
        bodyPart.AddForce(-velocity.normalized * (gunSpeed / 2), ForceMode.Impulse);
        // send back info like if stats are involved
        GetComponent<EnemyMovement>().enabled = false;
    }

    void EnableRagdoll()
    {
        GetComponent<CharacterController>().enabled = false;
        GetComponent<Animator>().enabled = false;
    }

}
