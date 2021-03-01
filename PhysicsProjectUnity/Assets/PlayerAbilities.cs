using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAbilities : MonoBehaviour
{
    Rigidbody playerRb;

    //Jetpack
    bool jetpackAbility = true;
    public float jetpackForce = 20f;
    public float maxJetpackFuel = 100f;
    public float jetpackFuelConsumptionRate = 10f;
    public float jetpackFuelRecovery = 2f;
    public float currentJetpackFuel = 0f;

    void Start()
    {
        playerRb = GetComponent<Rigidbody>();

        currentJetpackFuel = maxJetpackFuel;
    }

    void Update()
    {
        if (jetpackAbility)
        {
            if (Input.GetKey(KeyCode.E))
            {
                if (currentJetpackFuel > 0f)
                {
                    playerRb.AddForce(Vector3.up * jetpackForce);
                    currentJetpackFuel -= jetpackFuelConsumptionRate;
                }
            }
            else
            {
                if (currentJetpackFuel > maxJetpackFuel)
                {
                    currentJetpackFuel = maxJetpackFuel;
                }
                else if(currentJetpackFuel < 0f)
                {
                    currentJetpackFuel = 0f;
                }
                else
                {
                    currentJetpackFuel += Time.deltaTime * jetpackFuelRecovery;
                }
            }
        }

    }
}
