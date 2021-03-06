using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RocketAttack : MonoBehaviour
{
    Vector3 direction = Vector3.zero;
    float rocketForce = 0;
    float blastForce = 0;
    float hitRadius = 0;

    Rigidbody rb = null;

    LayerMask enemyLayerMask;

    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetRocket(Vector3 dir, float hitForce, float rbForce, float blastRadius, LayerMask enemyLayer)
    {
        rb = GetComponent<Rigidbody>();

        direction = dir;
        rocketForce = hitForce;
        blastForce = rbForce;

        hitRadius = blastRadius;
        enemyLayerMask = enemyLayer;

        rb.AddForce(dir * rocketForce, ForceMode.Impulse);
    }

    private void OnCollisionEnter(Collision collision)
    {
        Collider[] cols = Physics.OverlapSphere(transform.position, hitRadius, enemyLayerMask);
        foreach (Collider col in cols)
        {
            GameObject mainEnemyBody = col.transform.gameObject;
            bool checkGood = false;
            while (mainEnemyBody.transform.tag != "Enemy")
            {
                if (mainEnemyBody.transform.parent == null)
                    break;

                mainEnemyBody = mainEnemyBody.transform.parent.gameObject;
                if (mainEnemyBody.transform.tag == "Enemy")
                    checkGood = true;
            }
            if (checkGood)
            {
                mainEnemyBody.transform.GetComponent<EnemyHealth>().Death();
                mainEnemyBody.transform.GetChild(1).GetComponent<Rigidbody>().AddForce
                    (col.bounds.ClosestPoint(mainEnemyBody.transform.position).normalized * blastForce, ForceMode.Impulse);

            }
        }

        DestroyRocket();
    }

    void DestroyRocket()
    {
        // run rocket destruction particle stuff
        Destroy(gameObject);
    }
}
