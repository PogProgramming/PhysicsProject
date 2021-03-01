using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAbilities : MonoBehaviour
{
    Rigidbody playerRb;
    public LayerMask enemyLayer;

    //Jetpack
    bool jetpackAbility = true;
    public float jetpackForce = 20f;
    public float maxJetpackFuel = 100f;
    public float jetpackFuelConsumptionRate = 10f;
    public float jetpackFuelRecoveryRate = 2f;
    public float currentJetpackFuel = 0f;
    public RectTransform jetpackFuelDisplay = null;

    bool administratorAbilities = true;
    bool mosesAbility = true;
    float mosesRadius = 7f;

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
                else if(currentJetpackFuel < 100f)
                {
                    currentJetpackFuel += jetpackFuelRecoveryRate;
                    if (currentJetpackFuel > 100f)
                        currentJetpackFuel = 100f;
                }
            }

            if(jetpackFuelDisplay != null)
            {
                jetpackFuelDisplay.sizeDelta = new Vector2(jetpackFuelDisplay.sizeDelta.x, currentJetpackFuel);
            }
        }

        if (administratorAbilities)
        {
            if(Input.GetKey(KeyCode.O))
            {
                GameObject.Find("EventSystem").GetComponent<EnemySpawner>().SpawnEnemy();
            }

            if (Input.GetKeyDown(KeyCode.P))
            {
                mosesAbility = !mosesAbility;
            }

            if (mosesAbility)
            {
                RaycastHit objHit;
                if (Physics.SphereCast(transform.position, mosesRadius, transform.forward, out objHit, enemyLayer))
                {
                    Rigidbody rb = objHit.transform.GetComponent<Rigidbody>();
                    rb.AddForce(-objHit.normal * 500f);
                }
            }
        }

    }
}
